import { defineStore } from 'pinia'

export const useUserInfoStore = defineStore('userInfoStore', {
  state: () => ({
    email: '',
    password: '',
    username: '',
  }),
  getters: {},
  actions: {},
})
