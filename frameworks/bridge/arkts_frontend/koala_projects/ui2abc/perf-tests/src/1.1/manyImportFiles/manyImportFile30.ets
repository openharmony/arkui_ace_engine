
import { ManyImportComponent60 } from "./manyImportFile60"
import { ManyImportComponent61 } from "./manyImportFile61"


@Component
export struct ManyImportComponent30 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent60()
            ManyImportComponent61()

        }
    }
}
