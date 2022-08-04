## Como rodar

### Distribuido
```
cd distribuido/

ssh -R 10292:localhost:10292 <rasp_ip>

make
make cruzamento1
make cruzamento2
```
### Central
```
cd central/
yarn // install dependecies
yarn dev
```

## Limitações

- O servidor central deve ta executado antes do servidor distribuido
- O servidor central deve ser executado localmente
