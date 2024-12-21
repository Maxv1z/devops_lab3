FROM alpine:latest AS build

RUN apk add --no-cache build-base automake autoconf

WORKDIR /home/httpServer

COPY . .

RUN autoreconf --install
RUN ./configure
RUN make

FROM alpine:latest

WORKDIR /home/httpServer

COPY --from=build /home/httpServer/FuncA /home/httpServer/FuncA

RUN apk update && \
    apk add --no-cache libstdc++ libc6-compat

ENTRYPOINT ["/home/httpServer/FuncA"]
