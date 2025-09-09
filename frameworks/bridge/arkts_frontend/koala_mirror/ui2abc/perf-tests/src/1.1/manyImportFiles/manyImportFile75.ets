
import { ManyImportComponent150 } from "./manyImportFile150"
import { ManyImportComponent151 } from "./manyImportFile151"


@Component
export struct ManyImportComponent75 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent150()
            ManyImportComponent151()

        }
    }
}
