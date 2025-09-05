
import { ManyImportComponent88 } from "./manyImportFile88"
import { ManyImportComponent89 } from "./manyImportFile89"


@Component
export struct ManyImportComponent44 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent88()
            ManyImportComponent89()

        }
    }
}
