<template>
    <div class="Text">
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
                    <p>Text集合包含了一些常用的文本处理函数，包括分割、合并、删除等。</p>
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
                {//text_split
                    label: "text_split", comment: "文本_分割",
                    code: `std::vector<std::string> text_split(std::string text, std::string delimiter);`,
                    params: {
                        arr: [
                            { param: 'text', type: 'const std::string&', desc: '待分割的文本' },
                            { param: 'delimiter', type: 'const std::string&', desc: '分隔符' },
                        ],
                        ret: { type: 'std::vector<std::string>', desc: '分割后的文本数组' }
                    }
                }, {//text_join
                    label: "text_join", comment: "文本_合并",
                    code: `std::string text_join(std::vector<std::string> text_list, std::string delimiter = "");`,
                    params: {
                        arr: [
                            { param: 'text_list', type: 'const std::vector<std::string>&', desc: '待合并的文本数组' },
                            { param: 'delimiter', type: 'const std::string&', desc: '分隔符' },
                        ],
                        ret: { type: 'std::string', desc: '合并后的文本' }
                    }
                }, {//text_split_len
                    label: "text_split_len", comment: "文本_长度分割",
                    code: `std::vector<std::string> text_split_len(std::string text, size_t length = 1);`,
                    params: {
                        arr: [
                            { param: 'text', type: 'const std::string&', desc: '待分割的文本' },
                            { param: 'length', type: 'const size_t', desc: '分割长度' },
                        ],
                        ret: { type: 'std::vector<std::string>', desc: '分割后的文本数组' }
                    }
                }, {//text_left_del
                    label: "text_left_del", comment: "文本_左侧删除",
                    code: `std::string text_left_del(std::string text, size_t length = 1);`,
                    params: {
                        arr: [
                            { param: 'text', type: 'const std::string&', desc: '待删除的文本' },
                            { param: 'length', type: 'const size_t', desc: '待删除的长度' },
                        ],
                        ret: { type: 'std::string', desc: '删除后的文本' }
                    }
                }, {//text_right_del
                    label: "text_right_del", comment: "文本_右侧删除",
                    code: `std::string text_right_del(std::string text, size_t length = 1);`,
                    params: {
                        arr: [
                            { param: 'text', type: 'const std::string&', desc: '待删除的文本' },
                            { param: 'length', type: 'const size_t', desc: '待删除的长度' },
                        ],
                        ret: { type: 'std::string', desc: '删除后的文本' }
                    }
                }, {//text_find
                    label: "text_find", comment: "文本_寻找指定文本",
                    code: `int text_find(std::string text, std::string find_text);`,
                    params: {
                        arr: [
                            { param: 'text', type: 'const std::string&', desc: '被查找的文本' },
                            { param: 'find_text', type: 'const std::string&', desc: '待查找的文本' },
                        ],
                        ret: { type: 'int', desc: '找到的位置' }
                    }
                }, {//text_replace
                    label: "text_replace", comment: "文本_替换",
                    code: `std::string text_replace(std::string text, std::string find_text, std::string replace_text, size_t count = -1);`,
                    params: {
                        arr: [
                            { param: 'text', type: 'const std::string&', desc: '待替换的文本' },
                            { param: 'find_text', type: 'const std::string&', desc: '待查找的文本' },
                            { param: 'replace_text', type: 'const std::string&', desc: '待替换的文本' },
                            { param: 'count', type: 'const size_t', desc: '最大替换次数，-1表示全部替换' },
                        ],
                        ret: { type: 'std::string', desc: '替换后的文本' }
                    }
                }, {//text_to_wstr
                    label: "text_to_wstr", comment: "文本_转宽字符(不支持中文)",
                    code: `std::wstring text_to_wstr(std::string text);`,
                    params: {
                        arr: [
                            { param: 'text', type: 'const std::string&', desc: '待转换的文本' },
                        ],
                        ret: { type: 'std::wstring', desc: '转换后的文本' }
                    }
                }, {//text_to_str
                    label: "text_to_str", comment: "文本_转窄字符(不支持中文)",
                    code: `std::string text_to_str(std::wstring text);`,
                    params: {
                        arr: [
                            { param: 'text', type: 'const std::wstring&', desc: '待转换的文本' },
                        ],
                        ret: { type: 'std::string', desc: '转换后的文本' }
                    }
                }, {//text_base64_encode
                    label: "text_base64_encode", comment: "文本_base64编码",
                    code: `std::string text_base64_encode(std::string text);`,
                    params: {
                        arr: [
                            { param: 'text', type: 'const std::string&', desc: '待编码的文本' },
                        ],
                        ret: { type: 'std::string', desc: '编码后的文本' }
                    }
                }, {//text_base64_decode
                    label: "text_base64_decode", comment: "文本_base64解码",
                    code: `std::string text_base64_decode(std::string text);`,
                    params: {
                        arr: [
                            { param: 'text', type: 'const std::string&', desc: '待解码的文本' },
                        ],
                        ret: { type: 'std::string', desc: '解码后的文本' }
                    }
                }, {//text_gb2312_to_utf8
                    label: "text_gb2312_to_utf8", comment: "文本_GB2312编码转UTF8",
                    code: `std::string text_gb2312_to_utf8(std::string text);`,
                    params: {
                        arr: [
                            { param: 'text', type: 'const std::string&', desc: '待转换的文本' },
                        ],
                        ret: { type: 'std::string', desc: '转换后的文本' }
                    }
                }, {//text_utf8_to_gb2312
                    label: "text_utf8_to_gb2312", comment: "文本_UTF8编码转GB2312",
                    code: `std::string text_utf8_to_gb2312(std::string text);`,
                    params: {
                        arr: [
                            { param: 'text', type: 'const std::string&', desc: '待转换的文本' },
                        ],
                        ret: { type: 'std::string', desc: '转换后的文本' }
                    }
                }
            ],
            text: [
                `
    std::cout << Text::text_find("hello world", "world") << std::endl;//输出6
    //此Text集合包含了一些常用的文本处理函数，包括分割、合并、删除等。
    //类似于这种
                `,
                `
    /*
    * 文本_分割
    * @param text 待分割的文本
    * @param delimiter 分隔符
    * @return 分割后的文本数组
    */
    std::vector<std::string> text_split(std::string text, std::string delimiter);
    /*
    * 文本_合并
    * @param text_list 待合并的文本数组
    * @param delimiter 分隔符
    * @return 合并后的文本
    */
    std::string text_join(std::vector<std::string> text_list, std::string delimiter = "");
    /*
    * 文本_长度分割
    * @param text 待分割的文本
    * @param length 分割长度
    * @return 分割后的文本数组
    */
    std::vector<std::string> text_split_len(std::string text, size_t length = 1);
    /*
    * 文本_左侧删除
    * @param text 待删除的文本
    * @param length 待删除的长度
    * @return 删除后的文本
    */
    std::string text_left_del(std::string text, size_t length = 1);
    /*
    * 文本_右侧删除
    * @param text 待删除的文本
    * @param length 待删除的长度
    * @return 删除后的文本
    */
    std::string text_right_del(std::string text, size_t length = 1);
    /*
    * 文本_寻找指定文本
    * @param text 被查找的文本
    * @param find_text 待查找的文本
    * @return 找到的位置
    */
    int text_find(std::string text, std::string find_text);
    /*
    * 文本_替换
    * @param text 待替换的文本
    * @param find_text 待查找的文本
    * @param replace_text 待替换的文本
    * @param count 最大替换次数，-1表示全部替换
    * @return 替换后的文本
    */
    std::string text_replace(std::string text, std::string find_text, std::string replace_text, size_t count = -1);
    /*
    * 文本_转宽字符(不支持中文)
    * @param text 待转换的文本
    * @return 转换后的文本
    */
    std::wstring text_to_wstr(std::string text);
    /*
    * 文本_转窄字符(不支持中文)
    * @param text 待转换的文本
    * @return 转换后的文本
    */
    std::string text_to_str(std::wstring text);
    //====================================编码转换====================================
    /*
    * 文本_base64编码
    * @param text 待编码的文本
    * @return 编码后的文本
    */
    std::string text_base64_encode(std::string text);
    /*
    * 文本_base64解码
    * @param text 待解码的文本
    * @return 解码后的文本
    */
    std::string text_base64_decode(std::string text);
    /*
    * 文本_GB2312编码转UTF8
    * @param text 待转换的文本
    * @return 转换后的文本
    */
    std::string text_gb2312_to_utf8(std::string text);
    /*
    * 文本_UTF8编码转GB2312
    * @param text 待转换的文本
    * @return 转换后的文本
    */
    std::string text_utf8_to_gb2312(std::string text);
                `
            ],
        }
    }
};
</script>
<style lang="scss" scoped>
.Text {
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
