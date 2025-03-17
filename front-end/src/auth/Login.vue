<template>
  <form
    class="w-1/2 flex flex-col justify-center items-center p-4 gap-2 shadow-bottom rounded-md"
    action="#"
  >
    <div class="my-2 text-3xl font-semibold">
      <h1>LOGO</h1>
    </div>
    <!-- 邮箱 -->
    <label class="input validator">
      <svg class="h-[1em] opacity-50" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24">
        <g
          stroke-linejoin="round"
          stroke-linecap="round"
          stroke-width="2.5"
          fill="none"
          stroke="currentColor"
        >
          <rect width="20" height="16" x="2" y="4" rx="2"></rect>
          <path d="m22 7-8.97 5.7a1.94 1.94 0 0 1-2.06 0L2 7"></path>
        </g>
      </svg>
      <input type="email" placeholder="mail@site.com" required />
    </label>
    <div class="validator-hint hidden">请输入邮箱</div>
    <!-- 密码 -->
    <label class="input validator">
      <svg class="h-[1em] opacity-50" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24">
        <g
          stroke-linejoin="round"
          stroke-linecap="round"
          stroke-width="2.5"
          fill="none"
          stroke="currentColor"
        >
          <path
            d="M2.586 17.414A2 2 0 0 0 2 18.828V21a1 1 0 0 0 1 1h3a1 1 0 0 0 1-1v-1a1 1 0 0 1 1-1h1a1 1 0 0 0 1-1v-1a1 1 0 0 1 1-1h.172a2 2 0 0 0 1.414-.586l.814-.814a6.5 6.5 0 1 0-4-4z"
          ></path>
          <circle cx="16.5" cy="7.5" r=".5" fill="currentColor"></circle>
        </g>
      </svg>
      <input
        type="password"
        required
        placeholder="密码"
        minlength="8"
        pattern="(?=.*\d)(?=.*[a-z])(?=.*[A-Z]).{8,}"
        title="Must be more than 8 characters, including number, lowercase letter, uppercase letter"
      />
    </label>
    <p class="validator-hint hidden">
      Must be more than 8 characters, including
      <br />At least one number <br />At least one lowercase letter <br />At least one uppercase
      letter
    </p>
    <!-- 验证码 -->
    <input type="text" placeholder="请输入验证码" class="input" />

    <!-- 记住密码 -->
    <fieldset class="fieldset p-4 bg-base-100 border border-base-300 rounded-box w-64">
      <legend class="fieldset-legend">Login options</legend>
      <label class="fieldset-label">
        <input type="checkbox" class="checkbox checkbox-accent" />
        <div class="flex items-center w-full justify-between">
          <label for="rememberPw" class="text-black text-sm">记住我</label>
          <button class="btn btn-link">忘记密码？</button>
        </div>
      </label>
    </fieldset>

    <!-- 按钮 -->
    <div class="flex gap-2">
      <button class="btn btn-outline btn-accent">登录</button>
      <button class="btn btn-outline btn-secondary">注册</button>
    </div>
  </form>
</template>

<script setup></script>

<style lang="scss" scoped></style>
