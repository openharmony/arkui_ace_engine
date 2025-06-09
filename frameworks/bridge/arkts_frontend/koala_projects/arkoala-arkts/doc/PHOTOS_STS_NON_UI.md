# ArkTS NEXT Photos (NON-UI)

## Objective

Write in STS the non-UI business logic of Photos ohos app.

## Overview

The main screen of Photos application does essentially the following:
   1. Gets permissions to access user Album
   2. Access user Album and get image URLs
   3. Show a lazy List of Images with the data fetched from the URLs

This task is about being able to be able to get to 1 and 2.

Don't spend your time on any UI yet!

## ArkTS NEXT, static VM and HAP

The work is to be performed in the Blue zone on an RK Board.

Don't mess with the Phone yet!

You need to have the latest Blue zone @panda/sdk available here:
https://nexus.bz-openlab.ru:10443/#browse/browse:koala-npm

The static virtual machine is already available in the latest firmware for RK Board.

The HAP packing and example for sts is to be found here:
https://gitee.com/openharmony-sig/arkcompiler_ets_frontend/blob/master/arkoala-arkts/package.json#L41

The loading process is described here:
https://gitee.com/openharmony-sig/arkcompiler_ets_frontend/blob/master/arkoala-arkts/README.md


## Task break-down

### HAP Signature

To access user Album need to sign HAP with a special signature.

### OHOS interfaces access

You need to access

   * @ohos.file.photoAccessHelper
   * @ohos.abilityAccessCtrl
   * @ohos.data.dataSharePredicates

Don't over-engineer the access.
Treat @ohos libraries as just native libraries for now.

### The permissions

An example of permission access can be found here:

https://rnd-gitlab-msc.huawei.com/rus-os-team/koala-ui/koala-apps/-/blob/photo-mock-1/photo_mock_1/Photo_mockup/entry/src/main/ets/pages/Index.ets#L54


### Album access

The access to user Album is done by PhotoAccessHelper.
See for example Demo2 and Demo3 here:
https://wiki.huawei.com/domains/4997/wiki/47233/WIKI202312262627801?title=_e72501e6


## Expected result

The program should acquire the premissions, fetch the image URLs and print them to ohos log.

