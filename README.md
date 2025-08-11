# Reconhecedor de Palavras em Autômato Finito Determinístico (AFD)

Este projeto, desenvolvido para a disciplina de **Linguagens Formais e Autômatos**, implementa um sistema de reconhecimento de palavras baseado em **Autômatos Finitos Determinísticos (AFDs)**, utilizando linguagem **C**.  
O programa carrega a definição de um AFD a partir de um arquivo `.txt`, imprime a gramática regular equivalente e permite testar palavras quanto à aceitação no autômato.

---

## 👥 Integrantes
- Abdo Almagid Mahmud Rahal  
- Carlos Eduardo Patricio Remboski  
- Joao Vitor Vicentini Ribeiro  

---

## 📂 Organização do Projeto
├── main.c → Ponto de entrada do programa. Gerencia o menu principal.
├── afd.c → Implementação das funções para manipulação do AFD.
├── afd.h → Definições e protótipos de funções relacionadas ao AFD.

---

## 🚀 Funcionalidades
- Leitura de um AFD a partir de um arquivo `.txt`
- Impressão da gramática regular equivalente ao autômato
- Validação de palavras com base nas transições do AFD

---

## 📖 Como Usar o Programa

### 1. Menu Principal:
1. Inserir autômato → Lê um arquivo .txt com a definição do AFD
   
2.Sair → Encerra o programa

### 2. Submenu AFD (após carregar um autômato):
1. Testar palavra → Verifica se uma palavra é aceita pelo AFD

2. Voltar → Retorna ao menu principal

---

## 📝 Formato do Arquivo de Entrada (.txt)
O arquivo deve seguir o seguinte formato:

alfabeto={a,b,c,0,1,2}
estados={q0,q1,q2,q3,q4,q5}
finais={q2,q5}
(q0,a)=q1
(q1,a)=q2
(q1,b)=q1
(q1,0)=q4
(q2,c)=q3
(q3,b)=q2
(q3,0)=q5
(q4,0)=q2
(q4,1)=q5
(q5,2)=q4
