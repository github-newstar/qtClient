import Signup from '@/auth/Signup.vue'
import { createRouter, createWebHistory } from 'vue-router'
import Login from '../auth/Login.vue'
const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/signup',
      name: 'signup',
      component: () => import('../auth/Signup.vue'),
    },
    {
      path: '/',
      name: 'login',
      component: () => import('../auth/Login.vue'),
    },
    // {
    //   path: '/about',
    //   name: 'about',
    //   // route level code-splitting
    //   // this generates a separate chunk (About.[hash].js) for this route
    //   // which is lazy-loaded when the route is visited.
    //   component: () => import('../views/AboutView.vue'),
    // },
  ],
})

export default router
