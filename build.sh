export GOGCCFLAGS="-fPIC"
go build -ldflags '-s -w --extldflags "-static -fpic"' -buildmode=c-shared -o goso.so
