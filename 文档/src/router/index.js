import { createRouter, createWebHashHistory } from 'vue-router'
const routes = [
    {
        path: '/:pathWatch(.*)*',
        name: 'Home',
        component: () => import('../views/AEXModule.vue'),
    }, {

        path: '/Box/:type/:title',
        name: 'Box',
        component: () => import('../components/Box.vue'),
    }
];
const router = createRouter({
    history: createWebHashHistory(),
    routes
});
export default router;