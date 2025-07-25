### How to sync with specification tests

- Go to ```ets-plugin/test/specification/ets2bundle```
- Assert that both gitee and gitlab remotes configured, should be something like:
```
[core]
repositoryformatversion = 0
filemode = true
bare = false
logallrefupdates = true
[remote "gitee"]
url = https://gitee.com/openharmony/developtools_ace_ets2bundle.git
fetch = +refs/heads/*:refs/remotes/origin/*
[remote "gitlab"]
url = ssh://git@rnd-gitlab-msc.huawei.com:2222/rus-os-team/koala-ui/ets2bundle.git
fetch = +refs/heads/*:refs/remotes/origin/*h
```
- Pull changes from origin ```git reset --hard gitee master```
- Make some patches at ```ets-plugin/test/specification/patches``` if needed
- Push to gitlab ```git push gitlab master -f```