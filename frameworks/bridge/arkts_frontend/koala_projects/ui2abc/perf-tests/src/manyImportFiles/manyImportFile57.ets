
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent114 } from "./manyImportFile114"
import { ManyImportComponent115 } from "./manyImportFile115"


@Component
export struct ManyImportComponent57 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent114()
            ManyImportComponent115()

        }
    }
}
