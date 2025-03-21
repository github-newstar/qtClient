<template>
  <div class="chat-container mx-5 mb-8 mt-5">
    <div class="grid h-[90vh] md:grid-cols-5">
      <aside class="col-span-1 hidden md:block rounded-l-2xl bg-gray-800/50 backdrop-blur-md p-4">
        <h2 class="text-white">导航栏</h2>
      </aside>
      <main class="col-span-full md:col-span-4 rounded-r-2xl overflow-hidden bg-gray-900/50 backdrop-blur-md p-4">
        <div class="chat-window h-full flex flex-col">
          <div class="messages flex-1 overflow-y-auto p-4">
            <div class="message mb-4 flex items-start">
              <img src="../assets/img/head_2.jpg" alt="User Avatar" class="w-10 h-10 rounded-full mr-3">
              <div class="message-bubble bg-blue-600 text-white p-3 rounded-lg">
                <p>这是一个聊天气泡。</p>
              </div>
            </div>
            <div class="message mb-4 flex items-start justify-end">
              <div class="message-bubble bg-gray-700 text-white p-3 rounded-lg">
                <p>这是另一个聊天气泡。</p>
              </div>
              <img src="../assets/img/head_1.jpg" alt="User Avatar" class="w-10 h-10 rounded-full ml-3">
            </div>
          </div>
          <div class="chat-input mt-4 flex items-center">
            <input type="text" class="flex-1 p-3 rounded-lg bg-gray-800 text-white" placeholder="输入消息...">
            <button class="ml-3 p-3 rounded-lg bg-blue-600 text-white">发送</button>
          </div>
        </div>
      </main>
    </div>
  </div>
</template>

<script setup></script>

<style scoped>
.chat-container {
  background: linear-gradient(135deg, #1e1e1e, #1e2c3b);
  border-radius: 1rem;
  padding: 1rem;
}

.messages {
  max-height: 70vh;
}

.message-bubble {
  max-width: 70%;
}

.chat-input input {
  border: none;
  outline: none;
}

.chat-input button {
  border: none;
  outline: none;
  cursor: pointer;
}
</style>
