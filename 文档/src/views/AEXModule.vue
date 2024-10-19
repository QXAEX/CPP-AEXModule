<template>
    <div class="AEXModule">
        <div class="box">
            <div class="item" v-for="(item, index) in AEXModule.List" :key="index">
                <div>
                    <a v-if="item?.name" @click="item.link ? goToBox(item.link, item.type, item.msg) : Dwonload()">{{
                item.name
            }}</a>
                </div>
                <p>
                    <span v-text="`更新时间：${item.update}`"></span>
                    <br />
                    <span v-text="item.desc"></span>
                    <br />
                    <span v-if="item.type" v-text="`${item.type}`"></span>
                </p>
            </div>
        </div>
    </div>
</template>

<script setup>
import AEXModule from "../assets/AEXModule";
import { useRouter } from "vue-router";
const router = useRouter();
const props = defineProps({
    version: {
        type: String,
        default: "NULL"
    }
});
function goToBox(link, type, msg) {
    router.push({ path: `Box/${type}/${link}`, query: { msg: JSON.stringify(msg) } });
}
function Dwonload() {
    window.open('https://www.baidu.com/s?wd=下载');
}
</script>

<style lang="scss" scoped>
.AEXModule {
    display: flex;
    justify-content: center;

    .box {
        width: 1000px;

        .item {
            margin: 15px 0;
            padding: 15px 10px;
            line-height: 30px;

            * {
                color: #af3d8f;
            }

            div {
                display: flex;
                justify-content: center;

                a {
                    transition: transform 0.3s ease-in-out;
                    font-size: 24px;
                    text-decoration: none;
                    background: linear-gradient(to right, #69398d, #dc52b6, #69398d);
                    -webkit-background-clip: text;
                    -webkit-text-fill-color: transparent;
                    user-select: none;
                    cursor: pointer;

                    &:hover {
                        transform: scale(1.1);
                    }
                }
            }

            p {
                padding: 5px;

                border: {
                    left: 2px solid #af3d8f;
                    right: 2px solid #af3d8f;
                    bottom: 2px solid #af3d8f;
                    bottom-left-radius: 5px;
                    bottom-right-radius: 5px;
                }
            }
        }
    }
}
</style>