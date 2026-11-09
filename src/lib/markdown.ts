import { Marked } from "marked";
import { createHighlighter, type Highlighter, type ThemeRegistration } from "shiki";

/** Colours of the Kattis code editor (Ace "Tomorrow Night"). */
const kattisNight: ThemeRegistration = {
  name: "kattis-night",
  type: "dark",
  colors: { "editor.background": "#1d1f21", "editor.foreground": "#c5c8c6" },
  tokenColors: [
    { settings: { foreground: "#c5c8c6" } },
    { scope: ["comment", "punctuation.definition.comment"], settings: { foreground: "#969896" } },
    {
      scope: [
        "keyword", "keyword.control", "storage", "storage.type", "storage.modifier",
        "keyword.other.using", "punctuation.definition.directive", "meta.preprocessor keyword",
      ],
      settings: { foreground: "#b294bb" },
    },
    { scope: ["keyword.other.namespace", "keyword.other.namespace.directive", "keyword.operator"], settings: { foreground: "#8abeb7" } },
    { scope: ["constant.numeric", "constant.language", "constant.character.escape"], settings: { foreground: "#de935f" } },
    { scope: ["string", "punctuation.definition.string"], settings: { foreground: "#b5bd68" } },
    {
      scope: [
        "string.quoted.other.lt-gt.include",
        "string.quoted.other.lt-gt.include punctuation.definition.string",
        "meta.preprocessor.include string",
        "meta.preprocessor.include punctuation.definition.string",
      ],
      settings: { foreground: "#c5c8c6" },
    },
    {
      scope: ["entity.name.function", "entity.name.type", "support", "variable", "punctuation", "entity.name.namespace"],
      settings: { foreground: "#c5c8c6" },
    },
  ],
};

let hl: Promise<Highlighter> | undefined;

export async function renderMarkdown(md: string): Promise<string> {
  const h = await (hl ??= createHighlighter({ themes: [kattisNight], langs: ["cpp"] }));
  const marked = new Marked({
    renderer: {
      code({ text, lang }) {
        const html = h.codeToHtml(text, { lang: lang || "cpp", theme: "kattis-night" });
        return `<div class="code">
  <div class="code-bar">
    <span class="code-file">solution.cpp</span>
    <span class="code-lang">C++</span>
    <button type="button" class="copy" data-copy>Copy</button>
  </div>${html}</div>`;
      },
    },
  });
  const html = marked.parse(md) as string;
  // wrap tables so they scroll horizontally on small screens
  return html.replace(/<table>/g, '<div class="table"><table>').replace(/<\/table>/g, "</table></div>");
}
