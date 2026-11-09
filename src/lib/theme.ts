export const THEME_KEY = "kdcp-theme";

/** Runs in <head> before first paint so a saved choice never flashes the other theme. */
export const themeScript = `try{var t=localStorage.getItem("${THEME_KEY}");if(t==="light"||t==="dark")document.documentElement.dataset.theme=t}catch(e){}`;
