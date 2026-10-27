import socketserver,http.server,json,os,time,base64,subprocess,urllib.request,urllib.error,threading
os.makedirs('/data/notifications',exist_ok=True)
lock=threading.Lock()
def b64(x):return base64.urlsafe_b64encode(x).rstrip(b'=').decode()
def token():
 h=b64(json.dumps({'alg':'RS256','typ':'JWT','kid':'cluster-test'}).encode());p=b64(json.dumps({'scope':'compute_ctl:admin','aud':['compute'],'exp':int(time.time())+300}).encode());m=(h+'.'+p).encode()
 sig=subprocess.check_output(['openssl','dgst','-sha256','-sign','/secrets/compute-jwt.pem'],input=m)
 return m.decode()+'.'+b64(sig)
class Handler(http.server.BaseHTTPRequestHandler):
 def do_GET(self):
  self.send_response(200);self.end_headers();self.wfile.write(b'{}')
 def do_PUT(self):self.notify()
 def do_POST(self):self.notify()
 def notify(self):
  try:
   body=json.loads(self.rfile.read(int(self.headers.get('Content-Length','0'))));tid=body['tenant_id'];kind=self.path.strip('/');status=423
   with lock:
    json.dump(body,open('/data/notifications/'+tid+'.'+kind+'.json','w'),indent=2)
    for version in [16,17]:
     path='/configs/compute%d.json'%version
     if not os.path.exists(path):continue
     conf=json.load(open(path));settings=conf['spec']['cluster']['settings'];vals={x['name']:x for x in settings}
     if vals['neon.tenant_id']['value']!=tid:continue
     if kind=='notify-attach':
      node=body['shards'][0]['node_id'];vals['neon.pageserver_connstring']['value']='host=ps%d port=6400'%node
     elif kind=='notify-safekeepers':
      peers=','.join('sk%d:5454'%x['id'] for x in body['safekeepers']);vals['neon.safekeepers']['value']=peers;conf['spec']['safekeepers_generation']=body['generation']
     else:continue
     json.dump(conf,open(path+'.tmp','w'),indent=2);os.replace(path+'.tmp',path)
     r=urllib.request.Request('http://compute%d:3080/configure'%version,data=json.dumps(conf).encode(),headers={'Content-Type':'application/json','Authorization':'Bearer '+token()},method='POST')
     try:
      with urllib.request.urlopen(r,timeout=20) as result:result.read();status=200
     except Exception as e:print('persisted, compute not ready:',version,str(e),flush=True)
   self.send_response(status);self.end_headers();self.wfile.write(b'{}')
  except Exception as e:
   print('HOOK_ERROR',str(e),flush=True);self.send_response(503);self.end_headers()
 def log_message(self,fmt,*args):print(fmt%args,flush=True)
class Server(socketserver.ThreadingMixIn,http.server.HTTPServer):
 daemon_threads=True
Server(('0.0.0.0',8080),Handler).serve_forever()
