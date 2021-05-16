[![Build Status](https://travis-ci.org/matveybaykalov/lab09.svg?branch=master)](https://travis-ci.org/matveybaykalov/lab09)

## Отчёт по лабораторной работе lab09

## Tasks

- [x] 1. Создать публичный репозиторий с названием **lab09** на сервисе **GitHub**
- [x] 2. Ознакомиться со ссылками учебного материала
- [x] 3. Получить токен для доступа к репозиториям сервиса **GitHub**
- [x] 4. Выполнить инструкцию учебного материала
- [x] 5. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Были выполнены команды tutorial
Задаём необходимые переменные.
```sh
$ export GITHUB_USERNAME=matveybaykalov
$ export PACKAGE_MANAGER='sudo apt'
$ export GPG_PACKAGE_NAME=gpg
```
устанавливаем xclip и необходимые алиасы.
```sh
$ $PACKAGE_MANAGER install xclip
$ alias gsed=sed
$ alias pbcopy='xclip -selection clipboard'
$ alias pbpaste='xclip -selection clipboard -o'
```
Переходим в рабочую директорию и активируем скрипт.
```sh
$ cd ${GITHUB_USERNAME}/workspace
$ pushd .
$ source scripts/activate
$ go get github.com/aktau/github-release
```
Клонируем репозиторий с предыдущей лабораторной работы и обновляем URL.
```sh
$ git clone https://github.com/${GITHUB_USERNAME}/lab08 projects/lab09
$ cd projects/lab09
$ git remote remove origin
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab09
```
Заменяем lab08 на lab09.
```sh
$ gsed -i 's/lab08/lab09/g' README.md
```
В данном блоке команд мы устанавливаем gpg. Затем выводим уже существующие ключи и задаём формат отображения идентификаторов ключей. Потом генерируем ключ и снова выводим. Далее мы задаём две переменные GPG_KEY_ID и GPG_SEC_KEY_ID. Затем мы переводим GPG_KEY_ID в ASKII, копируем в буфер обмена и выводим его содержимое. Далее мы обновляем в конфигурацию git информацию о ключе gpg.
```sh
$ $PACKAGE_MANAGER install ${GPG_PACKAGE_NAME}
$ gpg --list-secret-keys --keyid-format LONG
$ gpg --full-generate-key
$ gpg --list-secret-keys --keyid-format LONG
$ gpg -K ${GITHUB_USERNAME}
$ GPG_KEY_ID=$(gpg --list-secret-keys --keyid-format LONG | grep ssb | tail -1 | awk '{print $2}' | awk -F'/' '{print $2}')
$ GPG_SEC_KEY_ID=$(gpg --list-secret-keys --keyid-format LONG | grep sec | tail -1 | awk '{print $2}' | awk -F'/' '{print $2}')
$ gpg --armor --export ${GPG_KEY_ID} | pbcopy
$ pbpaste
$ open https://github.com/settings/keys
$ git config user.signingkey ${GPG_SEC_KEY_ID}
$ git config gpg.program gpg
```
Проверяем, есть ли доступ к .bash_profile и записываем переменную GPG_TTY со значением $(tty). Такую же переменную записываем в файл .profile.
```sh
$ test -r ~/.bash_profile && echo 'export GPG_TTY=$(tty)' >> ~/.bash_profile
$ echo 'export GPG_TTY=$(tty)' >> ~/.profile
```
Запускаем комапилицию проекту и выполняем сборку с созданием пакета.
```sh
$ cmake -H. -B_build -DCPACK_GENERATOR="TGZ"
$ cmake --build _build --target package
```
Авторизируемся в сервисе travis и добавляем видимость текущему репозиторию.
```sh
$ travis login --auto
$ travis enable
```
Создаём метку и "подписываем" её ключом gpg
```sh
$ git tag -s v0.1.0.0
$ git tag -v v0.1.0.0
$ git show v0.1.0.0
$ git push origin master --tags
```
СОздаём релиз нашего пректа на GITHUB.
```sh
$ github-release --version
$ github-release info -u ${GITHUB_USERNAME} -r lab09
$ github-release release \
    --user ${GITHUB_USERNAME} \
    --repo lab09 \
    --tag v0.1.0.0 \
    --name "libprint" \
    --description "my first release"
```
Загружаем пакет в релиз на GITHUB.
```sh
$ export PACKAGE_OS=`uname -s` PACKAGE_ARCH=`uname -m` 
$ export PACKAGE_FILENAME=print-${PACKAGE_OS}-${PACKAGE_ARCH}.tar.gz
$ github-release upload \
    --user ${GITHUB_USERNAME} \
    --repo lab09 \
    --tag v0.1.0.0 \
    --name "${PACKAGE_FILENAME}" \
    --file _build/*.tar.gz
```

```sh
$ github-release info -u ${GITHUB_USERNAME} -r lab09
$ wget https://github.com/${GITHUB_USERNAME}/lab09/releases/download/v0.1.0.0/${PACKAGE_FILENAME}
$ tar -ztf ${PACKAGE_FILENAME}
```