FROM debian:jessie 

RUN apt-get update 
RUN apt-get -y install gcc 
RUN apt-get -y install make
RUN apt-get -y install nasm
RUN apt-get -y install qemu

WORKDIR /root

VOLUME ["/root/tp2"]

CMD ["bash"]
