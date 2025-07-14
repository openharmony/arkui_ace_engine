
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent78 } from "./manyImportFile78"
import { ManyImportComponent79 } from "./manyImportFile79"


@Component
export struct ManyImportComponent39 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent78()
            ManyImportComponent79()

        }
    }
}
