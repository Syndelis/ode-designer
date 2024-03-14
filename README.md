# ODE Designer

> [!IMPORTANT]
> Este projeto foi substituído pela re-implemantação da interface gráfica em Rust, neste repositório: https://github.com/Syndelis/ode-designer-rs/

## Contribuindo com o projeto

Siga os passos abaixo para conseguir clonar, buildar e desenvolver no projeto.

---

### <b> 1. Instale as dependências </b>

<details>
<summary><b>🐧 Para Debian/Ubuntu/Pop_OS!/ElementaryOS</b></summary>

```sh
$ sudo apt install build-essential cmake clang clang-format clang-tidy clangd
$ case $XDG_SESSION_TYPE in
    x11) sudo apt install xorg-dev ;;
    wayland) sudo apt install libwayland-dev libxkbcommon-dev wayland-protocols extra-cmake-modules;;
    *) echo "Não foi possível determinar o tipo de sessão que está sendo usada" ;;
esac
```
</details>

<details>
<summary><b>🐧 Para ArchLinux</b></summary>

```sh
$ sudo pacman -S gcc make cmake clang
$ case $XDG_SESSION_TYPE in
    x11) sudo pacman -S libx11 ;;
    wayland) sudo pacman -S wayland ;;
    *) echo "Não foi possível determinar o tipo de sessão que está sendo usada" ;;
esac
```
</details>

---

### <b> 2. Clone o repositório recursivamente </b>

Recomendamos a [ferramenta de linha de comando oficial do GitHub](https://cli.github.com/). Ela dará a você as permissões necessárias para criar branches e commitar no repositório. Adicionalmente, ela deixa que você faça diversas operações do GitHub diretamente da linha de comando.

<details>
<summary><b>⚠️ Se esta é a sua primeira vez usando o GitHub CLI</b></summary>

Rode o seguinte comando para fazer login na ferramenta:

```sh
$ gh auth login
```

Aceite sempre as primeiras opções (autenticação por HTTP, Abrir um Browser, etc.). Fique atento ao código que aparecerá no terminal. Você deve copiá-lo e colá-lo no navegador.

</details>

Para clonar o repositório com o GitHub CLI, rode o seguinte comando:

```sh
$ gh repo clone Syndelis/ode-designer -- --recursive
```

---

### <b> 3. Ative os hooks de pré-commit </b>

Isso permitirá que seu código seja formatado durante um `git commit`. Isto evitará que você adicione arquivos fora do padrão estabelecido. Quando isto acontecer, simplesmente revise as alterações, adicione-as e _commite_ novamente.

```sh
$ make enable-git-hooks
```

---

### <b> 4. Configure sua IDE </b>

As seguintes extensões são recomendadas e estão pré-configuradas para usar no VS Code:

- [clangd](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd): _Language Server_ de C e C++ baseado na LLVM <sup>(muito melhor do que o IntelliSense da MicroSoft)</sup>. Adiciona _autocompletions_ e referências de classes/funções/métodos;
- [CodeLLDB](https://marketplace.visualstudio.com/items?itemName=vadimcn.vscode-lldb): Permite que o código seja depurado direto da IDE;

Para outras IDEs, procure o que te atende suas necessidades e contribua para este README!

---

## Informações Adicionais

### Paletas de cores utilizadas no Software

- Nós:
    - Base: https://coolors.co/palette/edae49-d1495b-00798c-30638e-003d5b;
    - Highlight: https://coolors.co/palette/ef476f-ffd166-06d6a0-118ab2-073b4c

- Pins & Links: https://coolors.co/1b998b-2364aa-ed254e-dccca3-cae5ff
