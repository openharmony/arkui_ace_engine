
import { ManyImportComponent200 } from "./manyImportFile200"


@Component
export struct ManyImportComponent100 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent200()

        }
    }
}
