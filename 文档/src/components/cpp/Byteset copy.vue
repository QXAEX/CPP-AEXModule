<template>
    <div class="">
        <div class="info">
            <div class="item" style="flex: 100%;">
                <h2>main方法使用</h2>
                <pre v-html="utils.highlightCppKeywords(text[0])"></pre>
            </div>
            <div class="item" style="width: 800px;">
                <h2>可存储类型/构造函数/运算操作</h2>
                <pre v-html="utils.highlightCppKeywords(text[1])"></pre>
            </div>
            <div class="item" style="flex: 40%;height: 50%;padding: 0;">
                <div class="item" style="height: 50%;">
                    <h2>描述</h2>
                    <p>此类型对象可以支持相当多的类型(如果不够就联系作者,看看能不能酌情添加)。</p>
                </div>
                <div class="item" style="height: 50%;" v-for="(item, i) in list" :key="i">
                    <h2 v-text="item.label"></h2>
                    <pre v-html="utils.highlightCppKeywords(item.code)"></pre>
                    <p class="comment" v-text="item.comment"></p>
                    <h3>参数说明</h3>
                    <table class="params-table">
                        <tr class="top">
                            <th>参数名</th>
                            <th>类型</th>
                            <th>说明</th>
                        </tr>
                        <tr class="param" v-for="(param, i) in item.params.arr" :key="i">
                            <td>
                                <span class="dict">{{ param.param }}</span>
                            </td>
                            <td>
                                <span class="dict">{{ param.type }}</span>
                            </td>
                            <td v-html="param.desc"></td>
                        </tr>
                        <tr class="ret">
                            <td>
                                <span class="dict">返回值</span>
                            </td>
                            <td>
                                <span class="dict" v-text="item.params.ret.type"></span>
                            </td>
                            <td v-text="item.params.ret.desc"></td>
                        </tr>
                    </table>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
export default {
    props: ['utils'],
    data() {
        return {
            list: [
                {//从字符串构造
                    label: "Byteset", comment: "从字符串构造",
                    code: `Byteset(const std::string& str);`,
                    params: {
                        arr: [
                            { param: "str", type: "const std::string&", desc: "字符串" }
                        ],
                        ret: { type: "void", desc: "无返回值" }
                    }
                }
            ],
            text: [
                `
                `,
                `
                `
            ]
        }
    }
};
</script>
<style lang="scss" scoped>
.byteset {
    .info {
        display: flex;
        justify-content: center;
        flex-wrap: wrap;


        * {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }

        .item {
            position: relative;
            overflow: hidden;
            line-height: 2em;
            padding: 10px 0;
            box-sizing: border-box;

            h2 {
                font-style: oblique;
                background-color: #8111cb;
                padding: 5px 10px;
                display: inline-block;
                border-top-left-radius: 5px;
                border-top-right-radius: 5px;

                &::before {
                    position: absolute;
                    content: "";
                    width: 110%;
                    height: 2px;
                    background-color: #8111cb;
                    left: -10px;
                    top: 2.15em;
                }
            }

            h3 {
                background-color: #9b62c2;
                padding: 5px 10px;
                display: inline-block;
                border-top-left-radius: 5px;
                border-top-right-radius: 5px;

                &::before {
                    position: absolute;
                    content: "";
                    width: 110%;
                    height: 2px;
                    background-color: #9b62c2;
                    left: -10px;
                    margin-top: 2em;
                }
            }

            .comment {
                font-size: 1.2em;
                text-indent: 0.5em;
                margin: 5px 0;
            }

            pre {
                font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
                line-height: 1em;
                display: block;
                width: 100%;
                border-radius: 5px;
                padding: 15px 0;
                background-color: #1c1c1c;
                overflow: auto;
                font-size: 1.3rem;
            }

            .params-table {
                display: block;
                border-collapse: collapse;
                width: 100%;
                overflow: auto;


                th,
                td {
                    border: 1px solid #9b62c2;
                    padding: 8px;
                    text-align: left;
                    text-wrap: nowrap;
                }

                .top th {
                    user-select: none;
                    font-size: 1.2em;
                    font-style: oblique;
                    background-color: #8648b0;
                    text-align: center;

                    &:nth-child(3) {
                        text-align: left;
                    }
                }

                .dict {
                    background-color: #795c8c;
                    padding: 5px 10px;
                    font-weight: bold;
                    border-radius: 100px;
                }

                .param td,
                .ret td {
                    text-align: center;

                    &:nth-child(3) {
                        text-align: left;
                        width: 100%;
                    }
                }
            }
        }
    }
}
</style>
