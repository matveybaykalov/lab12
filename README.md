## Отчёт по лабораторной работе lab12

## Tasks

- [x] 1. Создать публичный репозиторий с названием **lab12** на сервисе **GitHub**
- [x] 2. Выполнить инструкцию учебного материала
- [x] 3. Ознакомиться со ссылками учебного материала
- [x] 4. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial
Устанавливаем переменные необходимые для выполнения лабораторной работы
```ShellSession
$ export GITHUB_USERNAME=matveybaykalov
$ export HUNTER_VERSION=2.0.5
```
Открываем учебное пособие по vim на русском языке
```ShellSession
$ vimtutor ru
```
Клонируем репозиторий с предыдущей добораторной работы и изменяем URL.
```ShellSession
$ git clone https://github.com/${GITHUB_USERNAME}/lab11 lab12
$ cd lab12
$ git remote remove origin
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab12
```
Открываем файл README.md и добавляем в него строчку, после чего закрываем и сохраняем файл.
```ShellSession
$ vim README.md
:s/lab11/lab12/g
/file<CR>wChaving the path environment variable value **LOG_PATH**<ESC>
:wq
```
Отредакируем файл demo.cpp, добавив переменную окружения LOG_PATH.
```ShellSession
$ vim sources/demo.cpp
Yp3wct>cstdlib<ESC>
/while<CR>ostd::string log_path = std::getenv("LOG_PATH");<ESC>
/"log<CR>
cf"log_path<ESC>
k2dd2kpVj<
:wq
```
Создаём дополнительную ветку и делаем релиз
```ShellSession
$ pushd $HUNTER_ROOT
$ git config --global hub.protocol https
$ git fork
$ git branch -u ${GITHUB_USERNAME}/master master
...
$ git release create -m"${HUNTER_VERSION}.1" ${HUNTER_VERSION}.1
$ git release show ${HUNTER_VERSION}.1
```
Для проверки скачиваем полученный архив.
```ShellSession
$ wget https://github.com/${GITHUB_USERNAME}/hunter/archive/${HUNTER_VERSION}.1.tar.gz
$ export MYHUNTER_SHA1=`openssl sha1 ${HUNTER_VERSION}.1.tar.gz | cut -d'=' -f2 | cut -c2-41`
$ echo $MYHUNTER_SHA1
$ rm -rf ${HUNTER_VERSION}.1.tar.gz
```
Обновляем хеш сумму в файле CMakeLists.txt
```ShellSession
$ popd
$ echo $MYHUNTER_SHA1 | pbcopy
$ vim CMakeLists.txt
/SHA1<CR>
wc2w<C-V><ESC>
:wq
```
Добавляем все изменения, комитим и отправляем на удалённый сервер.
```ShellSession
$ git add .
$ git commit -m"refactoring"
$ git push origin master
```
Логинимся в travis и включаем видимость репозитория.
```ShellSession
$ travis login --auto
$ travis enable
```