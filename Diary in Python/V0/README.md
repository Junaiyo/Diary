# Como usar

- Edite o dicionário `all`, adicione e remova quantas categorias quiser.
- Dentro da categoria que você criou, faça as anotações nesse estilo: `"Anotação {N}," (conteúdo) "Ended{N}."`.
- O anotação e o ended não podem ser removidos.
- Caso queira mudar o Anotação e o Ended, você pode editar ele na função `FindAnot` e `TotalAnots`, trocando todos os `f"Anotação"` e `f"Ended` por sua preferência.
- **Note** que se você remover os marcadores de números do `Anotação` e `Ended`, você terá que arranjar um jeito de contar as anotações totais de um jeito diferente na função `TotalAnots`,
- Caso você queira realmente mudar esse estilo de contagem, você teria que alterar as funções `TotalAnots`, `FindAnot` completamente/ou grande parte.
