
import { ManyImportComponent120 } from "./manyImportFile120"
import { ManyImportComponent121 } from "./manyImportFile121"


@Component
export struct ManyImportComponent60 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent120()
            ManyImportComponent121()

        }
    }
}
