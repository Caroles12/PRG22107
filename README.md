# PRG22107
Repositório da disciplina de programação orientada a objetos.

Esse projeto tem o objetivo de criar uma interface de controle para o sistema de acionamento de uma fechadura. Assim, ele é composto por dois projetos, sendo eles:

1. simulacaoFechaduraFinal : Projeto que simula a fechadura física, possibilitando a escolha da abertura de três portas diferentes via senha ou tagRFID.
2. controleAcessoFechadura: Projeto que contém uma interface gráfica de controle de acesso para a fechadura.

Desse modo, no controle de acesso da fechadura estão disponíveis as seguintes funcionalidades:

| Funcionalidade            | Objetivo                                                     |
| ------------------------- | ------------------------------------------------------------ |
| Login de usuário          | Somente usuários com login de usuário e senha tem acesso ao controle de acessos |
| Habilitar Fechadura       | Destravar as fechaduras através da interface de controle     |
| Estado Atual da Fechadura | Obter os status das portas                                   |
| Acionar Alarme            | Acionar alarme para as três portas                           |
| Cadastrar Usuário         | Cadastro de usuários para o acesso de controle               |
| Controle de Acesso        | Todos os registros de acessos das fechaduras                 |
| Remover Usuário           | Remover os usuários do acesso de controle                    |

Assim, a interface gráfica de controle gerada tem o seguinte perfil:

<img src= "![interfaceagente](C:\Users\carol\Documents\PRG22107\interfaceagente.png)"/>

Assim, para guardar todos os registros, foi utilizado o banco de dados SQLite, sendo necessário fazer a cópia da database para o ambiente local.

