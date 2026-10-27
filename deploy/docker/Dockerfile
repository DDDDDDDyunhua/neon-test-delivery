FROM neon-runtime-centos8:20261026
COPY kernel /opt/neon-kernel
ENV PATH=/opt/neon-kernel/bin:/opt/neon-kernel/pg_install/v17/bin:/usr/bin:/bin
ENV LD_LIBRARY_PATH=/opt/neon-kernel/pg_install/v17/lib:/opt/neon-kernel/pg_install/v16/lib
WORKDIR /data
USER 1000:1000

COPY runtime-locale /usr/lib/locale
