import pandas as pd
import plotly.graph_objects as go
from plotly.subplots import make_subplots
import numpy as np
from scipy.optimize import least_squares
from sklearn.metrics import r2_score

def read_data_file(filename):
    """Lê o arquivo de dados e retorna um DataFrame formatado"""
    df = pd.read_csv(filename, header=None)
    df.columns = ['Ordenado', 'Inverso', 'Aleatório']
    df['Tamanho'] = [100, 1000, 10000, 100000]
    return df

def complexity_function(n, complexity_type):
    """Retorna o valor da função de complexidade para um dado n"""
    if complexity_type == 'linear':
        return n
    elif complexity_type == 'linearithmic':
        return n * np.log2(n)
    elif complexity_type == 'quadratic':
        return n * n
    
def normalize_complexity_curve(sizes_data, tempos, complexity_type):
    """
    Normaliza a curva de complexidade e retorna o fator de escala e R²
    """
    def objective(params, x, y, complexity_type):
        scale = params[0]
        return scale * complexity_function(x, complexity_type) - y
    
    # Encontra o melhor fator de escala
    result = least_squares(
        objective, 
        x0=[1e-6],
        args=(sizes_data, tempos, complexity_type)
    )
    
    scale_factor = result.x[0]
    
    # Calcula o R² do ajuste
    y_pred = scale_factor * complexity_function(sizes_data, complexity_type)
    r2 = r2_score(tempos, y_pred)
    
    return scale_factor, r2

def get_best_complexity(r2_scores):
    """Determina qual complexidade melhor se ajusta aos dados"""
    best_complexity = max(r2_scores.items(), key=lambda x: x[1])
    return best_complexity[0]

def create_plot(movimentacoes_df, tempo_df, comparacoes_df):
# def create_plot(movimentacoes_df, tempo_df):
    """Cria os gráficos para cada métrica"""
    fig = make_subplots(
        rows=3, cols=1,
        subplot_titles=('Movimentações', 'Tempo de Execução (com Complexidades Teóricas)', 'Comparações'),
        vertical_spacing=0.15
    )
    
    colors = ['blue', 'red', 'green']
    entrada_tipos = ['Ordenado', 'Inverso', 'Aleatório']
    
    # Plota os dados reais
    for i, tipo in enumerate(entrada_tipos):
        # Gráfico de Movimentações
        fig.add_trace(
            go.Scatter(
                x=movimentacoes_df['Tamanho'],
                y=movimentacoes_df[tipo],
                name=f'{tipo} (Movimentações)',
                line=dict(color=colors[i]),
                showlegend=True
            ),
            row=1, col=1
        )
        
        # Gráfico de Tempo
        fig.add_trace(
            go.Scatter(
                x=tempo_df['Tamanho'],
                y=tempo_df[tipo],
                name=f'{tipo} (Tempo)',
                line=dict(color=colors[i]),
                showlegend=True
            ),
            row=2, col=1
        )
        
        # Gráfico de Comparações
        fig.add_trace(
            go.Scatter(
                x=comparacoes_df['Tamanho'],
                y=comparacoes_df[tipo],
                name=f'{tipo} (Comparações)',
                line=dict(color=colors[i]),
                showlegend=True
            ),
            row=3, col=1
        )

    # Configuração para as curvas de complexidade
    sizes_smooth = np.geomspace(100, 100000, 1000)
    complexity_types = {
        'linear': ('O(n)', 'rgba(128, 128, 128, 0.5)'),
        'linearithmic': ('O(n log n)', 'rgba(255, 165, 0, 0.5)'),
        'quadratic': ('O(n²)', 'rgba(255, 0, 0, 0.5)')
    }
    
    # Dicionário para armazenar as anotações
    annotations = []
    y_position = 1.15  # Posição inicial das anotações
    
    # Para cada tipo de entrada
    for i, tipo in enumerate(entrada_tipos):
        tempos = tempo_df[tipo].values
        sizes_data = tempo_df['Tamanho'].values
        
        # Armazena os R² para cada complexidade
        r2_scores = {}
        
        # Para cada tipo de complexidade
        for complexity_type, (name, color) in complexity_types.items():
            # Encontra o fator de escala e R²
            scale_factor, r2 = normalize_complexity_curve(
                sizes_data,
                tempos,
                complexity_type
            )
            
            r2_scores[complexity_type] = r2
            
            # Aplica o fator de escala à curva suave
            normalized_curve = scale_factor * complexity_function(sizes_smooth, complexity_type)
            
            # Adiciona a curva normalizada ao gráfico
            fig.add_trace(
                go.Scatter(
                    x=sizes_smooth,
                    y=normalized_curve,
                    name=f'{name} ({tipo})',
                    line=dict(
                        color=color,
                        dash='dash',
                        width=1
                    ),
                    showlegend=True
                ),
                row=2, col=1
            )
        
        # Determina a melhor complexidade
        best_complexity = get_best_complexity(r2_scores)
        complexity_names = {
            'linear': 'O(n)',
            'linearithmic': 'O(n log n)',
            'quadratic': 'O(n²)'
        }
        
        # Adiciona anotação
        annotations.append(dict(
            text=f"Melhor ajuste para {tipo}: {complexity_names[best_complexity]} (R² = {r2_scores[best_complexity]:.4f})",
            xref="paper", yref="paper",
            x=1.15, y=y_position - (i * 0.05),
            showarrow=False,
            font=dict(color=colors[i], size=12),
            align="left"
        ))

    # Atualiza o layout com as anotações
    fig.update_layout(
        height=1200,
        title_text="Métricas de Desempenho do Algoritmo de Ordenação",
        showlegend=True,
        legend=dict(
            yanchor="top",
            y=0.99,
            xanchor="left",
            x=1.05
        ),
        annotations=annotations
    )
    
    # Atualiza os eixos
    for row in [1, 2, 3]:
        fig.update_xaxes(title_text="Tamanho da Entrada", type="log", row=row, col=1)
    
    fig.update_yaxes(title_text="Número de Movimentações", type="log", row=1, col=1)
    fig.update_yaxes(title_text="Tempo (segundos)", type="log", row=2, col=1)
    fig.update_yaxes(title_text="Número de Comparações", type="log", row=3, col=1)
    
    return fig

def main():
    # Lê os arquivos de dados
    movimentacoes_df = read_data_file('movimentacoes.txt')
    tempo_df = read_data_file('tempo.txt')
    comparacoes_df = read_data_file('comparacoes.txt')
    
    # Cria os gráficos
    fig = create_plot(movimentacoes_df, tempo_df, comparacoes_df)
    # fig = create_plot(movimentacoes_df, tempo_df)

    # Salva o gráfico como HTML interativo
    fig.write_html('metricas_ordenacao.html')
    
    # Opcional: Mostra o gráfico diretamente
    fig.show()

if __name__ == "__main__":
    main()
