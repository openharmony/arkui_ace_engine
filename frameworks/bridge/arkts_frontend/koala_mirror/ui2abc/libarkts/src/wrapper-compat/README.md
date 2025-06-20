# koala-wrapper compatibility layer

THE CONTENT OF THIS FOLDER WILL BE REMOVED SOON, DO NOT MAKE ANY CHNGES HERE

> Synced from commit `9a450680e6d84afa55edb0bbc356a0d31824da16`
>
> _!4864 customdialog
Merge pull request !4864 from lishihao/customdialog_

## How to migrate
For each file in the `./arkts-api`:
1. Migrate the necessary changes to the `../src/arkts-api`
2. Remove the file
3. Add a reexport to the `./arkts-api/index.ts`

Once all the sources are be removed we can drop this compatibility layer at all
