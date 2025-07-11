
import { ManyImportComponent196 } from "./manyImportFile196"
import { ManyImportComponent197 } from "./manyImportFile197"


@Component
export struct ManyImportComponent98 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent196()
            ManyImportComponent197()

        }
    }
}
