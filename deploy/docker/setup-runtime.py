#!/usr/bin/env python3
"""Register the scoped EL8 runtime; keep existing Docker settings."""
import json, os, pathlib, shutil, subprocess, time
if os.geteuid()!=0: raise SystemExit('Run as root')
B='/opt/neon-cluster'
subprocess.check_call([B+'/runc-newseccomp','--version'])
p=pathlib.Path('/etc/docker/daemon.json'); p.parent.mkdir(exist_ok=True)
cfg=json.loads(p.read_text()) if p.exists() else {}
r=cfg.setdefault('runtimes',{})
entry={'path':B+'/neon-runc','runtimeArgs':[]}
if 'neon-runc' in r and r['neon-runc']!=entry:
    raise SystemExit('An incompatible neon-runc definition exists; review it manually.')
if p.exists(): shutil.copy2(str(p),str(p)+'.before-neon-'+str(int(time.time())))
r['neon-runc']=entry
tmp=str(p)+'.neon-new'
with open(tmp,'w') as f: json.dump(cfg,f,indent=2)
subprocess.check_call(['dockerd','--validate','--config-file',tmp])
os.replace(tmp,str(p))
subprocess.check_call(['systemctl','reload','docker'])
print('Registered neon-runc; system runc and default runtime were not replaced.')
