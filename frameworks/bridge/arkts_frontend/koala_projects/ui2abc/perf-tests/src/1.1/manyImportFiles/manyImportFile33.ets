
import { ManyImportComponent66 } from "./manyImportFile66"
import { ManyImportComponent67 } from "./manyImportFile67"


@Component
export struct ManyImportComponent33 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent66()
            ManyImportComponent67()

        }
    }
}
