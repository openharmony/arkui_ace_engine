
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent74 } from "./manyImportFile74"
import { ManyImportComponent75 } from "./manyImportFile75"


@Component
export struct ManyImportComponent37 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent74()
            ManyImportComponent75()

        }
    }
}
