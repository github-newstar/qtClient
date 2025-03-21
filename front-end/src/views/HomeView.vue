<template>
  <div>
    <div
      class="hero min-h-[90vh] w-full"
      style="
        background-image: url(https://img.daisyui.com/images/stock/photo-1507358522600-9f71e620c44e.webp);
      "
    >
      <div class="hero-overlay"></div>
      <div class="hero-content text-neutral-content text-center">
        <div class="max-w-md">
          <h1 class="mb-5 text-5xl font-bold">Hello there</h1>
          <p class="mb-5">
            EasyChat
            是一款为你而生的聊天应用，旨在提供最简洁、最直观的沟通体验。无论你是想与亲朋好友保持联系，还是与同事高效协作，EasyChat
            都让你能够轻松上手，即刻畅聊。我们专注于核心功能，去除冗余设计，让你专注于重要的对话，享受无压力的沟通乐趣。
          </p>
          <RouterLink :to="{ name: 'chatView' }">
            <button class="btn btn-primary">开始使用</button>
          </RouterLink>
        </div>
      </div>
    </div>
  </div>
</template>

<script setup>
import ChatView from './ChatView.vue'
</script>

<style lang="scss" scoped></style>
