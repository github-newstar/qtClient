import { createRouter, createWebHistory } from 'vue-router'
import HomeView from '../views/HomeView.vue'
import Signup from '@/auth/Signup.vue'
import Login from '../auth/Login.vue'
const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      name: 'homeview',
      component: () => import('../views/HomeView.vue'),
    },
    {
      path: '/signup',
      name: 'signup',
      component: () => import('../auth/Signup.vue'),
    },
    {
      path: '/login',
      name: 'login',
      component: () => import('../auth/Login.vue'),
      alias: ['/login'],
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
