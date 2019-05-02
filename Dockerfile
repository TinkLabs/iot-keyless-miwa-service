ARG node=stefanscherer/node-windows
ARG framework=mcr.microsoft.com/dotnet/framework/sdk
FROM $node as download

FROM $framework
ENV NPM_CONFIG_LOGLEVEL info

COPY --from=download /nodejs /nodejs
COPY --from=download /yarn /yarn
COPY --from=download /git /git

RUN $env:PATH = 'C:\nodejs;C:\yarn\bin;C:\git\cmd;C:\git\mingw64\bin;C:\git\usr\bin;{0}' -f $env:PATH ; \
    [Environment]::SetEnvironmentVariable('PATH', $env:PATH, [EnvironmentVariableTarget]::Machine)

COPY ./ /app
WORKDIR /app

RUN npm install

CMD ["npm.cmd", "start"]