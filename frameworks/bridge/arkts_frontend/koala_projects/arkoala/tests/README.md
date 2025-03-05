# How to run tests manually in `DevEco`

1. Build `arkoala.har` (see root `README.md`)

- it is referenced as `dependency` from `./app/oh-package.json5`

2. `npm run prepare-man-tests`

- takes components passed as `--generate-interface` in `arkoala/tools/peer-generator/package.json`
- adops matching tests from `./src/ets-tests/pages` and copies to the `DevEco` project to `./app/entry/src/main/ets/pages/tests`
- components not matching any test are logged to console

3. Open and run the `app` project in `DevEco`

- sign the project manually

4. Manually change `INDEX` in `./app/entry/src/main/ets/pages/Index.ets` to switch b/w test components