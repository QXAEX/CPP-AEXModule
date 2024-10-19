/*
 * @Function: 处理C++代码高亮关键词
 * @param {string} data 待处理的C++代码
 * @return {string} 处理后的C++代码
*/
export function highlightCppKeywords(data: string): string {
    const keywords: string[] = [
        'int', 'float', 'double', 'char', 'void', 'if', 'else', 'while', 'for', 'return',
        'class', 'struct', 'namespace', 'public', 'private', 'protected', 'static', 'const',
        'true', 'false', 'new', 'delete', 'this', 'nullptr', 'try', 'catch', 'throw',
        'default', 'long', 'short'
    ];

    const types: string[] = ['string', 'size_t'];

    // 替换特殊字符为 HTML 实体
    data = data.replace(/&/g, '&amp;')
        .replace(/</g, '&lt;')
        .replace(/>/g, '&gt;');

    // 高亮 #include 文件
    data = data.replace(/#include\s*<([^>]+)>/g, `#include <span style="color: orange;">&lt;$1&gt;</span>`);
    // 高亮字符串
    data = data.replace(/".*?"/g, `<span style="color: #ce9178;">$&</span>`);
    // 高亮数字
    data = data.replace(/\b(0x[\da-fA-F]+|\d+)\b/g, `<span style="color: #b5cea8;">$1</span>`);
    // 高亮注释
    data = data.replace(/(\/\*[\s\S]*?\*\/|\/\/[^\n]*)/g, `<span style="color: green;">$1</span>`);

    // 逐个关键词高亮
    keywords.forEach(keyword => {
        const regex = new RegExp(`\\b(${keyword})\\b`, 'g');
        data = data.replace(regex, `<span style="color: #569cd6;">$1</span>`);
    });

    // 逐个类型高亮
    types.forEach(type => {
        const regex = new RegExp(`\\b(${type})\\b`, 'g');
        data = data.replace(regex, `<span style="color: #4ec9b0;">$1</span>`);
    });

    // 高亮方法名
    const functionsRegex = /\b(\w+)\s*\(/g;
    data = data.replace(functionsRegex, (match, functionName) => {
        //yellow
        return `<span style="color: #f9bd1f;">${functionName}</span>(`;
    });

    // 添加换行效果，将 \n 替换为 <br>
    return data.replace(/\n/g, '<br>');
}
