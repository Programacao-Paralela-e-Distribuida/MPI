# Instalação Jupyter Notebook

Usar um `venv` (ambiente virtual) é a melhor prática e a forma correta de evitar problemas com pacotes para a instalação do servidor Jupyter localmente. 

Um `venv` cria uma "bolha" isolada para seu projeto. Tudo que você instalar com `pip` (como `jupyter`, `jupyter_http_over_ws`, etc.) ficará contido dentro dessa bolha, sem afetar o Python principal do seu sistema.

Aqui estão os passos. Vou dividir por sistema operacional, pois o comando de "ativação" é diferente.

## 1\. Escolha um Local e Crie o Ambiente

Primeiro, abra seu terminal e navegue (usando `cd`) para a pasta principal do seu projeto (ou onde você quer que o ambiente fique guardado).

Uma vez no diretório desejado, execute o comando para **criar** o ambiente. O comando usa o módulo `venv` do Python. É comum dar ao ambiente o nome de `venv`, `.venv` ou um nome descritivo.

Vamos usar `colab-env` como exemplo ( O "python3" pode ser apenas "python" dependendo do seu sistema):

```bash
python3 -m venv colab-env
```

Isso criará uma nova pasta chamada `colab-env` no diretório atual. Dentro dela estarão cópias do Python e do pip prontas para serem usadas.

-----

## 2\. Ative o Ambiente (O Passo Mais Importante)

Depois de criar, você precisa "entrar" ou **ativar** o ambiente. O terminal precisa saber que você quer usar o Python e o pip de dentro da pasta `colab-env`, e não os do sistema.

**Para macOS ou Linux:**

```bash
source colab-env/bin/activate
```

**Para Windows (usando o Prompt de Comando - `cmd.exe`):**

```bash
.\colab-env\Scripts\activate
```

**Para Windows (usando o PowerShell):**

```bash
.\colab-env\Scripts\Activate.ps1
```

*(Observação: Se o PowerShell der um erro sobre "execução de scripts", você talvez precise rodar `Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope Process` e tentar novamente).*

**Como saber se funcionou?**

Seu *prompt* do terminal mudará. Ele mostrará o nome do ambiente entre parênteses, algo assim:

`(colab-env) C:\seus\projetos>`
ou
`(colab-env) $`

Isso confirma que seu ambiente está **ativo**.

-----

## 3\. Use o Ambiente (Instale suas coisas)

Agora que o ambiente está ativo, qualquer comando `pip` que você rodar instalará pacotes *dentro* da pasta `colab-env`.

Este é o momento de instalar tudo o que você precisa para a conexão com o Colab:

```bash
# Garante que o pip está atualizado dentro do venv
pip install --upgrade pip

# Instala os pacotes necessários para o Jupyter e a conexão do Colab, nas versões adequadas

pip install \
    "notebook==6.5.5" \
    "jupyter_server==1.24.0" \
    "jupyter_client==7.4.9" \
    "nbclassic==0.5.5" \
    "jupyter_core==5.5.0" \
    "traitlets==5.9.0" \
    "tornado==6.2"
```

## 4\. Instalar e habilitar o pacote do Colab

```bash
pip install jupyter_http_over_ws
python -m jupyter serverextension enable --py jupyter_http_over_ws
python -m jupyter nbextension install --py jupyter_http_over_ws
python -m jupyter nbextension enable --py jupyter_http_over_ws
```

## 5\. Rodar o servidor Jupyter compatível com o Colab

```bash
jupyter notebook \
  --NotebookApp.allow_origin='https://colab.research.google.com' \
  --NotebookApp.port_retries=0 \
  --port=8888 \
  --NotebookApp.allow_credentials=True
````

## 6\. Saia do Ambiente (Quando terminar)

Quando você terminar seu trabalho e quiser voltar a usar o Python normal do seu sistema, basta digitar:

```bash
deactivate
```

O `(colab-env)` desaparecerá do seu prompt.

-----

### Conexão Final

Após executar este comando, copie uma das URL que irão aparecer no final do comando, tais como:

        http://localhost:8888/tree?token=483170b8244ed08718543f38acbde5cdeba5ea76b1d41405
        http://127.0.0.1:8888/tree?token=483170b8244ed08718543f38acbde5cdeba5ea76b1d41405

Cole esta URL no Google Colab, que será solicitada quando o comando `Conectar ao ambiente de execução local` for executado.

