<template>
  <Navbar />
  <main class="flex flex-col justify-center items-center w-full h-[100vh]">
    <RouterView />
  </main>
</template>

<script setup>
import Navbar from './assets/components/Navbar.vue'
</script>

<style lang="scss" scoped></style>
