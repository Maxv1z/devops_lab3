FROM alpine:latest

WORKDIR /home/httpServer

COPY ./FuncA /home/httpServer/FuncA

RUN apk update && \
    apk add --no-cache libstdc++ libc6-compat

ENTRYPOINT ["/home/httpServer/FuncA"]