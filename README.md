[![Build Status](https://travis-ci.org/matveybaykalov/task_timp_lab04.svg?branch=master)](https://travis-ci.org/matveybaykalov/lab08)

## Отчёт по лабораторной работе lab08

## Tasks

- [x] 1. Создать публичный репозиторий с названием **lab08** на сервисе **GitHub**
- [x] 2. Ознакомиться со ссылками учебного материала
- [x] 3. Выполнить инструкцию учебного материала
- [x] 4. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial
Создаём переменную необходимую для выполнения дабораторной работы.
```sh
$ export GITHUB_USERNAME=matveybaykalov
```
Переходим в рабочую дерикторию и активируем скрипт.
```
$ cd ${GITHUB_USERNAME}/workspace
$ pushd .
$ source scripts/activate
```
Клонируем репозиторий с предыдущей лабораторной работы в папку lab08 и обновляем URL.
```sh
$ git clone https://github.com/${GITHUB_USERNAME}/lab07 projects/lab08
$ cd lab08
$ git submodule update --init
$ git remote remove origin
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab08
```
Создаём файл Dockerfile и записываем в него информацию об образе, который будет использоваться.
```sh
$ cat > Dockerfile <<EOF
FROM ubuntu:18.04
EOF
```
Дополняем файл Dockerfile информацией о командах которые будут выполнены. Через эти команды мы обнавляем зависимости установленных приложений, а также устанавливаем программы необходдимые для работы написанной программы.
```sh
$ cat >> Dockerfile <<EOF

RUN apt update -y
RUN apt install -yy gcc g++ cmake
EOF
```
Копируем все файлы текущей директории в папку print и переходим в неё.
```sh
$ cat >> Dockerfile <<EOF

COPY . print/
WORKDIR print
EOF
```
Выполняем в докере команды по каомпиляции и сборке проекта
```sh
$ cat >> Dockerfile <<EOF

RUN cmake -H. -B_build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=_install
RUN cmake --build _build
RUN cmake --build _build --target install
EOF
```
Устанавливаем переменную окружения LOG_PATH для работы библиотки print.
```sh
$ cat >> Dockerfile <<EOF

ENV LOG_PATH /home/logs/log.txt
EOF
```
Через команду VOLUME передаём директорию, которая может быть монтирована.
```sh
$ cat >> Dockerfile <<EOF

VOLUME /home/logs
EOF
```
Устанавливаем рабочую директорию.
```sh
$ cat >> Dockerfile <<EOF

WORKDIR _install/bin
EOF
```
Устанавливаем точку входа
```sh
$ cat >> Dockerfile <<EOF

CMD ./demo
EOF
```
Соберём образ.
```sh
$ docker build -t logger .
```
Выведем информацию об образах.
```sh
$ docker images
```
Запустим докер в интерактивном режиме,протестируем программу demo и указываем директорию куда будут записаны логи.
```sh
$ mkdir logs
$ docker run -it -v "$(pwd)/logs/:/home/logs/" logger
text1
text2
text3
<C-D>
```
Посмотрим внутреннее состояние контейнера.
```sh
$ docker inspect logger
```
Просмотрим логи.
```sh
$ cat logs/log.txt
```
Отредактируем конфинурационный файл .travis.yml для того чтобы была возможность на сервисе travis создавать контейнер
```sh
$ vim .travis.yml
/lang<CR>o
services:
- docker<ESC>
jVGdo
script:
- docker build -t logger .<ESC>
:wq
```
Загружаем изменения в удалённый репозиторий.
```sh
$ git add Dockerfile
$ git add .travis.yml
$ git commit -m"adding Dockerfile"
$ git push origin master
```
Включаем видимость репозитория на travis
```sh
$ travis login --auto
$ travis enable
```