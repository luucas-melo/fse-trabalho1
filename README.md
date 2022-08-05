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

accessar http://localhost:3000
```

## Limitações

- O servidor central deve ta executado antes do servidor distribuido
- O servidor central deve ser executado localmente

## interface central

![image](https://user-images.githubusercontent.com/48891167/182980047-dfdd3151-89da-45d5-b22b-1e53f0d6dfb8.png)
