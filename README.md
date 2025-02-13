Este é um projeto de um chat simples desenvolvido em C++, utilizando sockets para comunicação entre clientes e servidor. O sistema permite que múltiplos usuários se conectem a um servidor central, troquem mensagens em tempo real e vejam as mensagens de outros participantes.

## Funcionalidades

- **Conexão de múltiplos clientes**: Vários usuários podem se conectar ao servidor simultaneamente.
- **Troca de mensagens em tempo real**: As mensagens enviadas por um usuário são transmitidas para todos os outros conectados.
- **Registro de histórico**: Todas as mensagens trocadas são salvas em um arquivo de log (`chat.log`) para consulta posterior.
- **Interface simples**: O chat é executado no terminal, com uma interface básica para envio e recebimento de mensagens.

## Estrutura do Projeto

- **Client**: Contém o código-fonte do cliente (`chat_client.cpp`), que se conecta ao servidor e permite ao usuário enviar e receber mensagens.
- **Server**: Contém o código-fonte do servidor (`chat_server.cpp`), que gerencia as conexões dos clientes e distribui as mensagens.
- **Configuração**: O arquivo `config.h` define as configurações comuns, como a porta de comunicação.

## Como Executar

1. **Compilar o servidor**:
   ```bash
   g++ server/chat_server.cpp -o server/chat_server -lpthread
   ./server/chat_server
Compilar o cliente:

bash
Copy
g++ client/chat_client.cpp -o client/chat_client
./client/chat_client
Conectar múltiplos clientes: Execute o cliente em diferentes terminais para simular múltiplos usuários.

Requisitos
Compilador C++ (ex: g++)

Sistema operacional compatível com sockets (Linux, macOS, ou Windows com WSL)

Contribuições
Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou enviar pull requests para melhorar o projeto.