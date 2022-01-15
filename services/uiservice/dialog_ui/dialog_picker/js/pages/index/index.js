import router from '@system.router'
import resourceManager from '@ohos.resourceManager';

export default {
    data: {
        title: 'World',
        shareHapList: [],
        lineNums: 6,
    },
    onInit() {
        let shareHap = [];
        for (let i = 0; i < this.hapList.length; i++) {
            shareHap.push(this.hapList[i]);
            if (i % this.lineNums == this.lineNums - 1 || i == this.hapList.length - 1) {
                this.shareHapList.push(shareHap);
                shareHap = [];
            }
        }
    },
    onShow() {
        this.$element('simplepanel').show();
    },
    onShare: function(item) {
        let param = item.bundle + ";" + item.ability;
        callNativeHandler('SHARE_EVENT', param);
    },
    changeSize: function(param) {
        callNativeHandler('CLOSE_EVENT', "");
    }
}
