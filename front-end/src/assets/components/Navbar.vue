<template>
  <div>
    <div class="navbar bg-neutral text-neutral-content flex justify-between">
      <RouterLink to="/">
        <button class="btn btn-ghost text-xl">EasyChat</button>
      </RouterLink>
      <RouterLink :to="{ name: 'login' }">
        <button class="btn btn-ghost text-xl">登录/注册</button>
      </RouterLink>
    </div>
  </div>
</template>

<script setup>
import login from '@/auth/Login.vue'
</script>

<style lang="scss" scoped></style>
