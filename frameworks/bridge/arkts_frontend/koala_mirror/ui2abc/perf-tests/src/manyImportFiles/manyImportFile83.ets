
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent166 } from "./manyImportFile166"
import { ManyImportComponent167 } from "./manyImportFile167"


@Component
export struct ManyImportComponent83 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent166()
            ManyImportComponent167()

        }
    }
}
