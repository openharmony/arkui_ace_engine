
import { ManyImportComponent24 } from "./manyImportFile24"
import { ManyImportComponent25 } from "./manyImportFile25"


@Component
export struct ManyImportComponent12 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent24()
            ManyImportComponent25()

        }
    }
}
