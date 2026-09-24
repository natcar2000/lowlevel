# lowlevel

Biblioteca de baixo nível para Python desenvolvida em **C**, utilizando `ctypes` para integração entre Python e uma DLL.

A `lowlevel` permite trabalhar com **memória bruta**, oferecendo operações de alocação, liberação, identificação, escrita e leitura de dados.

## Versão

**v1.0.0**

## Funcionalidades

- Alocação dinâmica de memória
- Liberação de memória
- Identificação de blocos por ID
- Escrita de dados em memória
- Leitura de dados em memória
- Gerenciamento interno das alocações
- Integração entre Python e C através de `ctypes`
- Compilação como DLL
- Manipulação de dados binários

## Arquitetura

```text
Python
   │
   │ ctypes
   ▼
memory.dll
   │
   ▼
Código C
   │
   ├── malloc()
   ├── free()
   ├── memcpy()
   ├── Allocation
   └── Queue
```

Cada bloco de memória possui um **ID numérico** utilizado para localizar a alocação.

## API Python

### `allocate(size)`

Aloca `size` bytes de memória.

```python
address = allocate(1024)
```

Retorna o endereço da memória alocada.

---

### `free(address)`

Libera a memória associada ao endereço.

```python
free(address)
```

---

### `get_id(address)`

Obtém o ID associado a uma alocação.

```python
allocation_id = get_id(address)
```

---

### `write(id, size, data)`

Escreve dados do tipo `bytes` na memória associada ao ID.

```python
data = b"Hello World!"

write(id, len(data), data)
```

---

### `read(id, size)`

Lê `size` bytes da memória associada ao ID e retorna os dados como `bytes`.

```python
data = read(id, len(data))

print(data)
```

## Exemplo

```python
data = b"Hello World!"

address = allocate(len(data))

try:
    id = get_id(address)

    write(id, len(data), data)

    result = read(id, len(data))

    print(result)

finally:
    free(address)
```

Resultado:

```text
b'Hello World!'
```

## Dados numéricos

A `lowlevel` trabalha com memória não tipada. Portanto, valores numéricos podem ser convertidos para bytes antes de serem armazenados.

```python
value = 123456

data = value.to_bytes(
    4,
    byteorder="little",
    signed=True
)

address = allocate(4)

try:
    id = get_id(address)

    write(id, 4, data)

    result = read(id, 4)

    value = int.from_bytes(
        result,
        byteorder="little",
        signed=True
    )

    print(value)

finally:
    free(address)
```

## Teste com áudio

A biblioteca também foi testada utilizando um arquivo de áudio.

O áudio foi:

1. carregado pelo Python como `bytes`;
2. armazenado na memória gerenciada pela DLL;
3. recuperado através de `read()`;
4. convertido novamente em dados utilizáveis pelo Python;
5. enviado ao `pygame`;
6. reproduzido com sucesso.

```text
Arquivo de áudio
       │
       ▼
     bytes
       │
       ▼
   allocate()
       │
       ▼
     write()
       │
       ▼
    Memória C
       │
       ▼
      read()
       │
       ▼
     bytes
       │
       ▼
    pygame
       │
       ▼
    Áudio
```

Esse teste demonstra que a biblioteca pode trabalhar com **dados binários arbitrários**, sem que o código C precise conhecer o tipo dos dados armazenados.

## Estrutura interna

Cada alocação é representada por uma estrutura contendo:

```c
typedef struct Allocation
{
    int id;
    void *memory;
    size_t size;
    void *copy;
    struct Allocation *next;
} Allocation;
```

As alocações são organizadas internamente por uma fila:

```c
typedef struct Queue
{
    Allocation *first;
    Allocation *last;
} Queue;
```

## Compilação

Utilizando GCC/MinGW-w64:

```bash
gcc -shared -Wall -Wextra -o memory.dll memory.c
```

A DLL gerada deve estar disponível para o código Python:

```text
memory.dll
```

## Tecnologias

- C
- Python
- `ctypes`
- GCC / MinGW-w64
- DLL
- pygame

## Status

**v1.0.0 — Concluída**

- [x] Alocação de memória
- [x] Liberação de memória
- [x] IDs para alocações
- [x] Escrita de bytes
- [x] Leitura de bytes
- [x] Integração Python/C
- [x] DLL funcional
- [x] Teste com valores numéricos
- [x] Teste com arquivo de áudio
- [x] Reprodução de áudio após passagem pela memória C

## Objetivo do projeto

A `lowlevel` foi desenvolvida como um projeto prático para estudar **programação de baixo nível, gerenciamento de memória, ponteiros, estruturas de dados, C e integração entre C e Python**.

O projeto também serve como base para futuras aplicações que necessitem manipular dados binários diretamente na memória.

---

**lowlevel v1.0.0**

Desenvolvido por **Natanael Rodrigues**.
