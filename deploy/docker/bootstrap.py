import http.client,urllib.request,urllib.error,json,time,subprocess,uuid,os
B='/opt/neon-cluster'; API='http://127.0.0.1:2234'
def _req(method,path,data=None):
 raw=None if data is None else json.dumps(data).encode()
 r=urllib.request.Request(API+path,data=raw,headers={'Content-Type':'application/json'},method=method)
 try:
  with urllib.request.urlopen(r,timeout=120) as x:
   body=x.read();return json.loads(body) if body else None
 except urllib.error.HTTPError as e:raise RuntimeError(str(e.code)+' '+path+' '+e.read().decode())
def req(method,path,data=None):
 for attempt in range(90):
  try:return _req(method,path,data)
  except Exception as e:
   if isinstance(e,RuntimeError) and not str(e).startswith("503"):raise
   if attempt==89:raise
   time.sleep(1)
def wait(url):
 for n in range(90):
  try:
   with urllib.request.urlopen(url,timeout=2) as x:
    if x.status==200:return
  except Exception:pass
  time.sleep(1)
 raise RuntimeError('not ready '+url)
wait(API+'/ready')
for i in [1,2]:
 print('register ps',i,flush=True)
 req('POST','/control/v1/node',{'node_id':i,'listen_pg_addr':'ps%d'%i,'listen_pg_port':6400,'listen_http_addr':'ps%d'%i,'listen_http_port':9898,'listen_grpc_addr':'ps%d'%i,'listen_grpc_port':51051,'availability_zone_id':'az%d'%i})
for i in [1,2,3]:
 print('register sk',i,flush=True)
 req('POST','/control/v1/safekeeper/%d'%i,{'id':i,'region_id':'local','version':1,'host':'sk%d'%i,'port':5454,'http_port':7676,'availability_zone_id':'az%d'%i})
subprocess.run([B+'/clusterctl','up','-d','ps1','ps2'],check=True)
for i in [1,2]:wait('http://127.0.0.1:%d/v1/status'%(21980+i))
print('ALL_STORAGE_NODES_READY',flush=True)
p=B+'/cluster-state.json'
if os.path.exists(p):state=json.load(open(p))
else:
 state={str(v):{'tenant_id':uuid.uuid4().hex,'timeline_id':uuid.uuid4().hex} for v in [16,17]};json.dump(state,open(p,'w'),indent=2)
for v in [16,17]:
 s=state[str(v)];tid=s['tenant_id'];tl=s['timeline_id']
 try:result=req('POST','/v1/tenant',{'new_tenant_id':tid,'placement_policy':{'Attached':1}})
 except RuntimeError as e:
  if not str(e).startswith('409'):raise
  result=req('GET','/control/v1/tenant/'+tid)
 print('tenant',v,result,flush=True)
 s['tenant_create_response']=result
 try:timeline=req('POST','/v1/tenant/'+tid+'/timeline',{'new_timeline_id':tl,'pg_version':v})
 except RuntimeError as e:
  if not str(e).startswith('409'):raise
  timeline=req('GET','/v1/tenant/'+tid+'/timeline/'+tl)
 s['timeline_response']=timeline
 json.dump(state,open(p,'w'),indent=2)
 print('timeline',v,timeline,flush=True)
 shards=result.get('shards',[])
 if shards:ps=shards[0].get('node_id',shards[0].get('node_attached'))
 else:
  desc=req('GET','/control/v1/tenant/'+tid);print('describe',desc,flush=True);ps=desc['shards'][0]['node_attached']
 s['pageserver_id']=ps
 config=json.load(open(B+'/configs/compute-template.json'))
 config['spec']['safekeepers_generation']=1
 config['compute_ctl_config']={'jwks':json.load(open(B+'/configs/jwks.json'))}
 settings=config['spec']['cluster']['settings']
 remove=['cron.database']
 settings=[x for x in settings if x['name'] not in remove]
 values={'fsync':'on','port':'5432','shared_buffers':'64MB','shared_preload_libraries':'neon','neon.tenant_id':tid,'neon.timeline_id':tl,'neon.pageserver_connstring':'host=ps%d port=6400'%ps,'neon.safekeepers':'sk1:5454,sk2:5454,sk3:5454','synchronous_commit':'on'}
 for x in settings:
  if x['name'] in values:x['value']=values.pop(x['name'])
 for k,val in values.items():settings.append({'name':k,'value':val,'vartype':'string'})
 config['spec']['cluster']['settings']=settings
 config['spec']['cluster']['cluster_id']='cluster-pg%d'%v
 config['spec']['cluster']['name']='cluster-pg%d'%v
 json.dump(config,open(B+'/configs/compute%d.json'%v,'w'),indent=2)
 os.chown(B+'/configs/compute%d.json'%v,1000,1000)
 json.dump(state,open(p,'w'),indent=2)
subprocess.run([B+'/clusterctl','up','-d','compute16','compute17'],check=True)
print('COMPUTES_STARTED',flush=True)
