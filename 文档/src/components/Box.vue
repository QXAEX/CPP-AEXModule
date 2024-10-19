<template>
    <div class="Box">
        <div class="top">
            <RouterLink :to="{ path: '/' }">&lt; BACK</RouterLink>
        </div>
        <div class="Title">
            <span>{{ route.query.msg.type }}</span>
            {{ route.params.title }}
        </div>
        <component :is="component" style="color: rgba(255,255,255, .7);" :utils="utils"></component>
    </div>
</template>

<script setup>
import * as utils from '../assets/utils';
import { ref, markRaw, onMounted } from 'vue';
import { useRoute, useRouter } from 'vue-router';

const component = ref(null);
const route = useRoute(), router = useRouter();
onMounted(() => {
    route.query.msg = JSON.parse(route.query.msg);
    import(`../components/${route.params.type}/${route.params.title}.vue`).then(module => {
        component.value = markRaw(module.default);
    }).catch(e => {
        import(`../components/error.vue`).then(module => {
            component.value = markRaw(module.default);
        });
    })
});
</script>

<style lang="scss" scoped>
.Box {

    .top {
        height: 50px;

        a {
            text-decoration: none;
            font-weight: bold;
            font-size: 20px;
        }
    }

    .Title {
        color: rgba(white, 0.8);
        text-align: center;
        font-size: 25px;
        margin-bottom: 15px;

        span {
            font-weight: bold;
            font-size: 28px;
            color: #0070c0;
        }
    }
}
</style>
