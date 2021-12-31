FROM golang:1.17.2-alpine as dev

ENV ROOT=/go/src/app
ENV CGO_ENABLED 0
WORKDIR ${ROOT}

RUN apk update && apk add git make
COPY go.mod go.sum ./
RUN go mod download
