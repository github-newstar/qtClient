<template>
  <Navbar />
  <main :class="isChatView ? 'w-full h-[90vh]' : 'flex flex-col justify-center items-center w-full h-[90vh]'">
    <RouterView />
  </main>
</template>

<script setup>
import { computed, ref } from 'vue';
import Navbar from './assets/components/Navbar.vue'
import { useRoute } from 'vue-router';

const route = useRoute();

const isChatView = computed(() => route.name === 'chatView');
</script>

<style lang="scss" scoped></style>
