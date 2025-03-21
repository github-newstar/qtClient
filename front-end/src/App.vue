<template>
  <Navbar />
  <main
    :class="
      isChatView ? 'w-full h-[90vh]' : 'flex flex-col justify-center items-center w-full h-[90vh]'
    "
  >
    <RouterView />
  </main>
</template>

<script setup>
import { computed, onMounted, onUpdated, ref } from 'vue'
import Navbar from './assets/components/Navbar.vue'
import { useRoute } from 'vue-router'
import { useUserInfoStore } from './stores/UserInfo'
import supabase from './utilities/supabase'

const userStore = useUserInfoStore()
const route = useRoute()

const isChatView = computed(() => route.name === 'chatView')

//获取用户登录状态
const checkUser = async () => {
  const localUser = await supabase.auth.getSession()
  userStore.setUserInfo(localUser.data.session.user.user_metadata)
}
onMounted(() => {
  checkUser()
})
onUpdated(() => {
  checkUser()
})
// userStore.setUserInfo();
</script>
