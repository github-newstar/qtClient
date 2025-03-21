<template>
  <div>
    <div class="navbar bg-neutral text-neutral-content flex justify-between z-1">
      <RouterLink to="/">
        <button class="btn btn-ghost text-xl">EasyChat</button>
      </RouterLink>
      <button v-if="userStore.username" @click="logOut" class="btn btn-link">登出</button>
      <template v-else>
        <RouterLink :to="{ name: 'login' }">
          <button class="btn btn-ghost text-xl">登录/注册</button>
        </RouterLink>
      </template>
    </div>
  </div>
</template>

<script setup>
import login from '@/auth/Login.vue'
import supabase from '@/utilities/supabase'
import { useUserInfoStore } from '@/stores/UserInfo'

const userStore = useUserInfoStore()

const logOut = async () => {
  userStore.logOut()
}
</script>

<style lang="scss" scoped></style>
