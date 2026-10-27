#!/usr/bin/env python3
"""Prepare a NEW installation; never overwrite an existing data directory."""
import base64, json, os, pathlib, re, subprocess
B = pathlib.Path(__file__).resolve().parent
if str(B) != '/opt/neon-cluster':
    raise SystemExit('Install this release at /opt/neon-cluster (runtime RPATH requirement).')
if (B/'data').exists() or (B/'secrets').exists():
    raise SystemExit('Existing data/secrets found. Stop: this command is for a fresh installation only.')
if os.geteuid() != 0:
    raise SystemExit('Run as root.')
for name in ['broker','control-db','controller','compute-hook','ps1','ps2','sk1','sk2','sk3','compute16','compute17','shared']:
    p=B/'data'/name; p.mkdir(parents=True); os.chown(str(p),1000,1000)
s=B/'secrets'; s.mkdir(mode=0o700); os.chown(str(s),1000,1000)
key=s/'compute-jwt.pem'
subprocess.check_call(['openssl','genrsa','-out',str(key),'2048'])
os.chmod(str(key),0o600); os.chown(str(key),1000,1000)
mod=subprocess.check_output(['openssl','rsa','-in',str(key),'-noout','-modulus']).decode().strip().split('=',1)[1]
def enc(b): return base64.urlsafe_b64encode(b).rstrip(b'=').decode()
jwks={'keys':[{'kty':'RSA','kid':'cluster-test','alg':'RS256','use':'sig','n':enc(bytes.fromhex(mod)),'e':'AQAB'}]}
with open(str(B/'configs/jwks.json'),'w') as f: json.dump(jwks,f,indent=2)
os.chown(str(B/'configs'),1000,1000)
for p in (B/'configs').iterdir():
    os.chown(str(p),1000,1000)
    os.chmod(str(p),0o755 if p.suffix=='.sh' else 0o644)
for name in ['clusterctl','neon-runc','runc-newseccomp']:
    os.chmod(str(B/name),0o755)
print('Prepared new directories and a NEW JWT key. No existing cluster data was imported.')
